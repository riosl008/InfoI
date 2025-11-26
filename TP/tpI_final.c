/*
github: https://github.com/riosl008/InfoI/tree/main/TP
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

struct memory {
  char *response;
  size_t size;
};

static size_t cb(char *data, size_t size, size_t nmemb, void *clientp)
{
  size_t realsize = nmemb;
  struct memory *mem = clientp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0;

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}

int get_json_value(const char *json, const char *key, char *out, int max)
{
	char *p = strstr(json, key);
	if(!p)
		return 0;
	p = strchr(p, ':');
	if(!p)
		return 0;
	p++;

	if(*p == '"')
	{
		p++;
		int i = 0;
		while(*p != '"' && i < max - 1)
		{
			out[i++] = *p++;
		}
		out[i] = 0;
		return 1;
	}

	int i = 0;
	while ((*p >= '0' && *p <= '9') && i < max - 1)
	{
		out[i++] = *p++;
	}
	out[i] = 0;
	return 1;
}

void escribir_log(const char *nombre, const char *mensaje, long fecha)
{
	FILE *f = fopen("log.txt", "a");
	if(!f)
		return;
	fprintf(f, "%lu - %s: %s\n", fecha, nombre, mensaje);
	fclose(f);

}
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Uso: ./bot token.txt\n");
		return 1;
	}

	char token[200];
	FILE *ft = fopen(argv[1], "r");
	if(!ft)
	{
		printf("Error: No se pudo abrir el archivo del token\n");
		return 1;

	}
	fgets(token, sizeof(token), ft);
	fclose(ft);

	token[strcspn(token, "\n")] = 0;

	long offset = 0;

	while (1)
	{
		CURL *curl = curl_easy_init();
    struct memory chunk = {0};

    if (curl)
    {
			char api_url[500];
      if (offset == 0)
      	snprintf(api_url, sizeof(api_url), "https://api.telegram.org/bot%s/getUpdates", token);
      else
        snprintf(api_url, sizeof(api_url), "https://api.telegram.org/bot%s/getUpdates?offset=%ld", token, offset);

      curl_easy_setopt(curl, CURLOPT_URL, api_url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

      curl_easy_perform(curl);

      if (chunk.response)																				//mensajes
      {
      	if (strstr(chunk.response, "\"update_id\""))
      	{
        	char update_id[50];
          char chat_id[50];
          char first_name[50];
          char text[200];
          char date[50];
          get_json_value(chunk.response, "\"update_id\"", update_id, 50);
          get_json_value(chunk.response, "\"id\"", chat_id, 50);
          get_json_value(chunk.response, "\"first_name\"", first_name, 50);
          get_json_value(chunk.response, "\"text\"", text, 200);
          get_json_value(chunk.response, "\"date\"", date, 50);
					long fecha = atol(date);
          long upd = atol(update_id);

         																												// Registrar log
          escribir_log(first_name, text, fecha);

         																												// Preparar respuesta
          char mensaje[300];
          if (strstr(text, "hola") || strstr(text, "Hola"))
          	snprintf(mensaje, sizeof(mensaje), "Hola%%20%s", first_name);
          else if (strstr(text, "chau") || strstr(text, "Chau"))
          	snprintf(mensaje, sizeof(mensaje), "Chau%%20%s", first_name);
          else
          	snprintf(mensaje, sizeof(mensaje), "No%%20entendi%%20tu%%20mensaje");

         																												 // Enviar respuesta
          char send_url[1200];
          	snprintf(send_url, sizeof(send_url), "https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s", token, chat_id, mensaje);

            curl_easy_setopt(curl, CURLOPT_URL, send_url);
            curl_easy_perform(curl);

           																												// Avanzar offset → evitar repetir
            offset = upd + 1;
					}
				}
        free(chunk.response);
        curl_easy_cleanup(curl);
			}
      sleep(2);  // espera
		}
    return 0;
}
