#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
	freopen("p0.dat", "r", stdin);

	double mn, mx, avr, num;
	scanf("%lf", &num);
	mn = num;
	mx = num;
	avr = num;
	for(int i = 0; i < 11; i++){
		scanf("%lf", &num);
		if(num > mx) mx = num;
		if(num < mn) mn = num;
		avr += num; 
	}
	avr /= 12.0;

	mx = abs(avr - mx);
	mn = abs(avr - mn);

	printf("%lf", avr);
	printf("%lf %lf %lf %lf", mx, mn, mx / avr, mn / avr);

	return 0;
}