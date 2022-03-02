/**
 * @file Test the running time of the code.
 * @author Jason M. Li
 * @copyright @see "LICENSE"
 * @version 1.0.0-Beta
 */

#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include <math.h>
#define MULTI_TIME 4
#define EXPECTED_MIN_MS 400
#define TEST_TIMES 20

void main_code() {
	// --- Please input your code here. ---
	// --- Please input your code here. ---
}

namespace TIMEIT {
	struct timeval tv_begin, tv_end;
	int i,
	j,
	test_times = 1;
	long long timediff;
	long long usedtime[TEST_TIMES];
	int avg_value;
	double sd_value;
	void printUsedtime() {
		printf("Test No. %d\n", i + 1);
		printf("Test for %d times\n", test_times);
		printf("Spend %d.%03dms\n", timediff / 1000, timediff % 1000);
		int avg_time = timediff * 1000 / test_times; // 单位：纳秒
		printf("Average: Spend \033[1;31m%dms %03dμs %03dns\033[0m\n\n", avg_time / 1000000, avg_time % 1000000 / 1000, avg_time % 1000);
	}
	/**
	 * @brief 计算标准差、平均数
	 */
	void sd() {
		double sd_num = 0;
		long long average_num = 0;
		for (int i=0; i<TEST_TIMES; i++) average_num += usedtime[i];
		average_num /= TEST_TIMES;
		avg_value = average_num;
		for (int i=0; i<TEST_TIMES; i++) sd_num += (average_num - usedtime[i]) * (average_num - usedtime[i]);
		sd_num /= TEST_TIMES;
		sd_value = sqrt(sd_num);
	}
}

int main() {
	for (TIMEIT::i=0; TIMEIT::i<TIMEIT::test_times; TIMEIT::i++) {
		gettimeofday(&TIMEIT::tv_begin, NULL);
		for (TIMEIT::j=0; TIMEIT::j<TIMEIT::test_times; TIMEIT::j++) main_code();
		gettimeofday(&TIMEIT::tv_end, NULL);
		TIMEIT::timediff = (TIMEIT::tv_end.tv_sec - TIMEIT::tv_begin.tv_sec) * 1000000LL + (TIMEIT::tv_end.tv_usec - TIMEIT::tv_begin.tv_usec);
		TIMEIT::printUsedtime();
		if (TIMEIT::timediff > EXPECTED_MIN_MS * 1000) break;
		TIMEIT::test_times *= MULTI_TIME;
	}
	printf("\n-------- Start formal test ---------\n\n");
	for (TIMEIT::i=0; TIMEIT::i<TEST_TIMES; TIMEIT::i++) {
		gettimeofday(&TIMEIT::tv_begin, NULL);
		for (TIMEIT::j=0; TIMEIT::j<TIMEIT::test_times; TIMEIT::j++) main_code();
		gettimeofday(&TIMEIT::tv_end, NULL);
		TIMEIT::timediff = (TIMEIT::tv_end.tv_sec - TIMEIT::tv_begin.tv_sec) * 1000000LL + (TIMEIT::tv_end.tv_usec - TIMEIT::tv_begin.tv_usec);
		TIMEIT::usedtime[TIMEIT::i] = TIMEIT::timediff * 1000 / TIMEIT::test_times;
		TIMEIT::printUsedtime();
	}
	TIMEIT::sd();
	printf("\n-------- Report --------\n\n");
	printf("Avg: \033[1;32m%dms %03dμs %03dns\033[0m\n", TIMEIT::avg_value / 1000000, TIMEIT::avg_value % 1000000 / 1000, TIMEIT::avg_value % 1000);
	printf("Std: %.6fms\n\n\n", TIMEIT::sd_value / 1000000);
	return 0;
}