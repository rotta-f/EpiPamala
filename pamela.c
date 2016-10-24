/* Define which PAM interfaces we provide */
#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

/* Include PAM headers */
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    // printf("USER: %s\n", user);

    pgd_ret = pam_get_data(pamh, "PAMELA_TOKEN_DATA", (const void **) &data);
    if (pgd_ret != PAM_SUCCESS || data == NULL) {
        return(PAM_IGNORE);
    }

    // printf("%s\n", data);

    char *file_name;
    int id_file;
    int fd;
    int sprintf_ret;

    srandom(42);
    id_file = random() % 268435456;
    if ((file_name = malloc(sizeof(char) * 20)) == NULL)
      return (PAM_IGNORE);
    sprintf_ret = sprintf(file_name, "/tmp/pam_%X");
    // printf("%s\n", file_name);
    if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
      return (PAM_IGNORE);
    write(fd, data, strlen(data));
    close(fd);

    char *cmd_line;
    int size;

    size = sprintf_ret + strlen("/usr/sbin/init_container.sh") + strlen(user) + 5;
    if ((cmd_line = malloc(sizeof(char) * (size))) == NULL)
      return (PAM_IGNORE);
    sprintf(cmd_line, "%s %s %s\n", "/usr/sbin/init_container.sh", user, file_name);
    system(cmd_line);
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
    // printf("USER: %s\n", user);

    pgd_ret = pam_get_data(pamh, "PAMELA_TOKEN_DATA", (const void **) &data);
    if (pgd_ret != PAM_SUCCESS || data == NULL) {
        return(PAM_IGNORE);
    }

    // printf("%s\n", data);

    char *cmd_line;
    int size;

    size = strlen("/usr/sbin/umount_container.sh") + strlen(user) + 5;
    if ((cmd_line = malloc(sizeof(char) * (size))) == NULL)
      return (PAM_IGNORE);
    sprintf(cmd_line, "%s %s\n", "/usr/sbin/umount_container.sh", user);
    system(cmd_line);

    printf("\\***** pam_sm_close_session *****/\033[00m\n");
    return(PAM_IGNORE);
}

/* PAM entry point for authentication verification */
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    // printf("\033[01;32m/***** pam_sm_auth *****\\\n");
    const char *user = NULL;
    const char *auth_tok = NULL;
    int pgu_ret;
    int pgautok_ret;
    int psd_ret;

    pgu_ret = pam_get_user(pamh, &user, NULL);
    if (pgu_ret != PAM_SUCCESS || user == NULL) {
        return(PAM_IGNORE);
    }
    // printf("USER: %s\n", user);

    pgautok_ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **) &auth_tok);
    if (pgautok_ret != PAM_SUCCESS || auth_tok == NULL) {
        return (PAM_IGNORE);
    }
    // printf("AUTHTOK: %s\n", auth_tok);

    char *data;
    if ((data = malloc(sizeof(char) * (strlen(auth_tok) + 1))) == NULL)
      return (PAM_IGNORE);
    if ((data = strcpy(data, auth_tok)) == NULL)
      return (PAM_IGNORE);

    psd_ret = pam_set_data(pamh, "PAMELA_TOKEN_DATA", (void *)data, NULL);
    if (psd_ret != PAM_SUCCESS || auth_tok == NULL) {
      return (PAM_IGNORE);
    }

    // printf("\\***** pam_sm_auth *****/\033[00m\n");
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
