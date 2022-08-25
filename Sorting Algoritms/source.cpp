#include "sort.h"



int main() {

	int sort_me[] = { 165, 125, -161, -230, -115, 184, -123, 8, -246, 101, -168, -248, -113, 93, -24, 13, 44, 28, 179, -65 };

	sort::Quick(sort_me, sizeof(sort_me) / sizeof(sort_me[0]));

	return 0;
}