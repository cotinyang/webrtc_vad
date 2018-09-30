#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "webrtc_vad.h"

void TestVAD(char *pAudioFile, int nSample, int nMode)
{
	VadInst *pVad = WebRtcVad_Create();
	if (pVad == NULL)
	{
		perror("WebRtcVad_Create failed!");
		return;
	}

	if (WebRtcVad_Init(pVad))
	{
		perror("WebRtcVad_Init failed!");
		return;
	}

	if (WebRtcVad_set_mode(pVad, nMode))
	{
		perror("WebRtcVad_set_mode failed!");
		return;
	}

	FILE *fp = NULL;
	FILE *fpR = NULL;
	fp = fopen(pAudioFile, "rb");
	fseek(fp, 0, SEEK_END);
	unsigned int nLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	short shBufferIn[160] = {0};
	while (1)
	{
		if (160 != fread(shBufferIn, 2, 160, fp))
			break;
		int nRet = WebRtcVad_Process(pVad, 16000, shBufferIn, 160);
		printf("%d", nRet);
	}

	fclose(fp);
	WebRtcVad_Free(pVad);
}

int main(int argc,char *argv[])
{
	if(argc < 3) return -1;
	TestVAD(argv[1], atoi(argv[2]), 3);
	return 0;
}
