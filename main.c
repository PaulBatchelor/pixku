#include <stdio.h>
#include <runt.h>
#include "pixku.h"

int main(int argc, char *argv[])
{
    return irunt_begin(argc, argv, pixku_runt_loader);
}
