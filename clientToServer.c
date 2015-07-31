#include <stdio.h>
#include <string.h>
 
#include <curl/curl.h>
 
int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;
 
  struct curl_httppost *formpost=NULL;
  struct curl_httppost *lastptr=NULL;
  struct curl_slist *headerlist=NULL;
  static const char buf[] = "Expect:";
 
  curl_global_init(CURL_GLOBAL_ALL);
  /* videoId */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "videoId",
               CURLFORM_COPYCONTENTS, "a",
               CURLFORM_END);
  /* userId */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "userId",
               CURLFORM_COPYCONTENTS, "2",
               CURLFORM_END);
  /* videoDangerPoint */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "videoDangerPoint",
               CURLFORM_COPYCONTENTS, "1",
               CURLFORM_END);
  /* videoDate */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "videoDate",
               CURLFORM_COPYCONTENTS, "abcd",
               CURLFORM_END);
  /* videoReason */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "videoReason",
               CURLFORM_COPYCONTENTS, "1",
               CURLFORM_END);
  /* visitorFace */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "visitorFace",
               CURLFORM_FILE, "C:\\Users\\youjin\\hyj\\img\\img1.jpg",
               CURLFORM_END);
  /* Fill in the file upload field */ 
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "videofile",
               CURLFORM_FILE, "C:\\Users\\youjin\\hyj\\video\\test1.avi",
               CURLFORM_END);
 
  /* Fill in the filename field */ 
  /*
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "filename",
               CURLFORM_COPYCONTENTS, "C:\\Users\\youjin\\hyj\\video\\test1.avi",
               CURLFORM_END);
	*/
 
  /* Fill in the submit field too, even if this is rarely needed */ 
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "submit",
               CURLFORM_COPYCONTENTS, "send",
               CURLFORM_END);
 
  curl = curl_easy_init();
  /* initialize custom header list (stating that Expect: 100-continue is not
     wanted */ 
  headerlist = curl_slist_append(headerlist, buf);
  if(curl) {
    /* what URL that receives this POST */ 
    curl_easy_setopt(curl, CURLOPT_URL, "http://210.125.96.109/upload.php");
    if ( (argc == 2) && (!strcmp(argv[1], "noexpectheader")) )
      /* only disable 100-continue header if explicitly requested */ 
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    /* then cleanup the formpost chain */ 
    curl_formfree(formpost);
    /* free slist */ 
    curl_slist_free_all (headerlist);
  }
  return 0;
}
