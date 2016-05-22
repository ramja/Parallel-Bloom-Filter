
double f(double);
double Trap(
	double left_endpt /* in */,
	double right_endpt /* in */,
	int trap_count /* in */,
	double base_len /* in */){
	double estimate;
	double x;
	int i;
	estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
	for(i = 1; i <=trap_count-1; i++){
		x=left_endpt + i*base_len;
		estimate += f(x);
	}

	estimate = estimate*base_len;
	return estimate;
}/*Trap*/
double f(double node){
	double value_f;
	value_f = node*node;
return value_f;
} /*f*/
	




