#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/net.h>
#include <net/netctl.h>
#include <sysutil/sysutil.h>
#include <io/pad.h>

// Endereco curto onde voce vai hospedar ou apontar o link (ex: seu servidor local HTTP ou proxy)
#define URL_SERVIDOR "http://192.168.1"
#define CAMINHO_DESTINO "/dev_hdd0/packages/download_ps3.pkg"

int main(int argc, char *argv[]) {
    padInfo padinfo;
    padData paddata;

    // Inicializa controles e rede do PS3
    ioPadInit(7);
    netInitialize();
    netCtlInit();

    printf("\n========================================\n");
    printf("   LinkDownload PS3 - Autor: Laxinha    \n");
    printf("========================================\n");
    printf("Pressione [X] para iniciar o download.\n");
    printf("Pressione [O] para sair.\n");

    while (1) {
        ioPadGetInfo(&padinfo);
        for (int i = 0; i < MAX_PADS; i++) {
            if (padinfo.status[i]) {
                ioPadGetData(i, &paddata);
                if (paddata.BTN_CROSS) {
                    printf("Iniciando conexao com o servidor...\n");
                    // Aqui entra a rotina de download via socket HTTP direto para /dev_hdd0/packages/
                    sleep(2);
                }
                if (paddata.BTN_CIRCLE) {
                    goto sair;
                }
            }
        }
        sysUtilCheckCallback();
        usleep(10000);
    }

sair:
    netCtlTerm();
    netDeinitialize();
    ioPadEnd();
    return 0;
}
