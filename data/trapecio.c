double f(double node);
double Trap(
	double left_epoint, /*in*/
	double right_epoint, /*in*/
	double base_len, /*in*/
	int trap_count /*in*/){
	double x=0.0;
	double estimate =0.0; 
	int i=0;
	estimate = (f(left_epoint)+f(right_epoint)) / 2.0;
	for (i=0; i<=trap_count-1; i++){
		x = left_epoint + i*base_len;
		estimate+=f(x);
	}
	return estimate*=base_len;
} /* Trap */

double f(double node){
	int value_f;
	value_f = node*node;
	return value_f;
}
