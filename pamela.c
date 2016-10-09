/* Define which PAM interfaces we provide */
#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

/* Include PAM headers */
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* PAM entry point for session creation */
int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    printf("\033[01;34m/***** pam_sm_open_session *****\\\n");
    const char *user = NULL;
    const char *data = NULL;
    int pgu_ret;
    int pgd_ret;

    pgu_ret = pam_get_user(pamh, &user, NULL);
    if (pgu_ret != PAM_SUCCESS || user == NULL) {
        return(PAM_IGNORE);
    }
    printf("USER: %s\n", user);

    pgd_ret = pam_get_data(pamh, "PAMELA_TOKEN_DATA", (const void **) &data);
    if (pgd_ret != PAM_SUCCESS || data == NULL) {
        return(PAM_IGNORE);
    }

    int i;
    for (i = 0; i < SHA512_DIGEST_LENGTH; i++) {
      printf("%X", data[i]);
    }
    printf("\n");

    printf("\\***** pam_sm_open_session *****/\033[00m\n");
    return(PAM_IGNORE);
}

/* PAM entry point for session cleanup */
int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    printf("\033[01;33m/***** pam_sm_close_session *****\\\n");
    const char *user = NULL;
    const char *data = NULL;
    int pgu_ret;
    int pgd_ret;

    pgu_ret = pam_get_user(pamh, &user, NULL);
    if (pgu_ret != PAM_SUCCESS || user == NULL) {
        return(PAM_IGNORE);
    }
    printf("USER: %s\n", user);

    pgd_ret = pam_get_data(pamh, "PAMELA_TOKEN_DATA", (const void **) &data);
    if (pgd_ret != PAM_SUCCESS || data == NULL) {
        return(PAM_IGNORE);
    }
    int i;
    for (i = 0; i < SHA512_DIGEST_LENGTH; i++) {
      printf("%X", data[i]);
    }
    printf("\n");

    printf("\\***** pam_sm_close_session *****/\033[00m\n");
    return(PAM_IGNORE);
}

/* PAM entry point for authentication verification */
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    printf("\033[01;32m/***** pam_sm_auth *****\\\n");
    const char *user = NULL;
    const char *auth_tok = NULL;
    int pgu_ret;
    int pgautok_ret;
    int psd_ret;

    pgu_ret = pam_get_user(pamh, &user, NULL);
    if (pgu_ret != PAM_SUCCESS || user == NULL) {
        return(PAM_IGNORE);
    }
    printf("USER: %s\n", user);

    pgautok_ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **) &auth_tok);
    if (pgautok_ret != PAM_SUCCESS || auth_tok == NULL) {
        return (PAM_IGNORE);
    }
    printf("AUTHTOK: %s\n", auth_tok);

    char *data = malloc(sizeof(char) * SHA512_DIGEST_LENGTH);
    SHA512(auth_tok, strlen(auth_tok), data);
    psd_ret = pam_set_data(pamh, "PAMELA_TOKEN_DATA", data, NULL);
    if (psd_ret != PAM_SUCCESS || auth_tok == NULL) {
      return (PAM_IGNORE);
    }

    printf("\\***** pam_sm_auth *****/\033[00m\n");
    return(PAM_IGNORE);
}

/*
PAM entry point for setting user credentials (that is, to actually
establish the authenticated user's credentials to the service provider)
*/
/*int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    printf("pam_sm_setcred\n");
    return(PAM_IGNORE);
}*/
