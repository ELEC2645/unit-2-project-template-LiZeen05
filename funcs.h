#ifndef FUNCS_H
#define FUNCS_H

void menu_item_1(void);
void menu_item_2(void);
void menu_item_3(void);
void menu_item_4(void);


//part 1
void ohmsLaw_calculator(void);
void series_R_calculator(void);
void parallel_R_calculator(void);
void rc_calculator(void);
void rl_calculator(void);
void power_calculator(void);

//part 2
double sine_wave(double t, double freq, double amp, double dc);
double square_wave(double t, double freq, double amp, double dc);
double sawtooth_wave(double t, double freq, double amp, double dc);
double triangle_wave(double t, double freq, double amp, double dc);
void ascii_plot(double *samples, int n, int height, int width);
int save_csv(const char *filename, double *samples, int n, double fs);

//part 3
double* read_csv(char *filename, int *n_out, double *fs_out);
void compute_stats(double *a, int n, double *mean, double *rms, double *minv, double *maxv);
double zero_freq(double *a, int n, double fs);
int main_freq(double *a, int n, double fs);

//part 4
void voltage_converter(void);
void current_converter(void);
void resistance_converter(void);
void power_converter(void);
void frequency_converter(void);
void capacitance_converter(void);
void inductance_converter(void);

#endif