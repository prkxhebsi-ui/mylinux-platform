#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(void)
{
    uid_t uid = getuid();
    gid_t gid = getgid();
    struct passwd *user = getpwuid(uid);
    struct group *group = getgrgid(gid);

    printf("uid=%u", (unsigned int)uid);

    if (user != NULL)
        printf("(%s)", user->pw_name);

    printf(" gid=%u", (unsigned int)gid);

    if (group != NULL)
        printf("(%s)", group->gr_name);

    printf("\n");

    return 0;
}
