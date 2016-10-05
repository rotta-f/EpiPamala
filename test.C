#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdio.h>

int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  printf("Open_session.\n");
  const void **item;

  int retvalue;
  retvalue = pam_get_item(pamh, PAM_AUTHTOK, item);
  printf("PAM_GET_ITEM: %s\n", pam_strerror(pamh, retvalue));
  printf("%p ITEM\n", *item);
  return(PAM_SUCCESS);
}

int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  printf("Close_session.\n");
  return(PAM_SUCCESS);
}

int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return(PAM_SUCCESS);
}

int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  printf("Authenticate.\n");
  return(PAM_SUCCESS);
}

int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return(PAM_SUCCESS);
}

int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return(PAM_SUCCESS);
}
