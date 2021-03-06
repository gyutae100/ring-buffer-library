// Ring Buffer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "CStreamSQ.h"

#include <iostream>
using namespace std;

#include <windows.h>
#include <stdlib.h>
#include <time.h>

CStreamSQ g_stream_q;

int main(){

	const char* src_string = { "a123456789a b123456789b c123456789c d123456789d e123456789e " };
	char *Input_string = NULL;
	char *output_string = NULL;
	int prev_Idx_Input = 0;
	int Input_num_random;
	int output_num_random;

	g_stream_q.ClearRingBuffer();

	while (1)
	{
		int retval;

		//srand((NULL));
		srand(time(NULL));
		Input_num_random = (rand() % 20) + 1;
		Input_string = new char[Input_num_random];

		for (int idx = 0; idx < Input_num_random; idx++) {

			Input_string[idx] = src_string[prev_Idx_Input++];

			if (prev_Idx_Input >= strlen(src_string)) {

				prev_Idx_Input -= strlen(src_string);
			}
		}

		retval = g_stream_q.Put(Input_string, Input_num_random);

		g_stream_q.DisplayInfo1();
		//Sleep(1000);

		if (Input_num_random != retval) {

			prev_Idx_Input -= Input_num_random - retval;

			if (prev_Idx_Input < 0) {

				prev_Idx_Input += strlen(src_string);
			}
		}

		output_num_random = (rand() % 20) + 1;
		output_string = new char[output_num_random + 1];

		//retval = g_stream_q.Get(output_string, output_num_random);
		retval = g_stream_q.Peek(output_string, output_num_random);
		retval = g_stream_q.Peek(output_string, output_num_random);
		g_stream_q.MoveFrontIdx(retval);


		output_string[retval] = '\0';

		printf("%s", output_string);

		g_stream_q.DisplayInfo2();
		Sleep(100);
	}


	delete[] Input_string;
	delete[] output_string;


}

