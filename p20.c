#include <stdio.h>

/* from racket:
 * (define (fact n) (if (<= n 1) 1 (* n (fact (- n 1)))))
 * (fact 100)
 */
const char kFact100[] =
"933262154439441526816992388562667004907159682643816214685929638"
"952175999932299156089414639761565182862536979208272237582511852"
"10916864000000000000000000000000";

int main() {
	int sum = 0;
	for (size_t i = 0; kFact100[i]; ++i)
		sum += kFact100[i] - '0';
	printf("%d\n", sum);
	return 0;
}
