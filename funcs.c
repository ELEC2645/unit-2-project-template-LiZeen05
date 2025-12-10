#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<math.h>
#include "funcs.h"

void ohmsLaw_calculator(){
    double V, I, R;
    int choice;

    printf("\nOhm's Law\n");
    printf("1. Calculate Voltage (V)\n");
    printf("2. Calculate Current (I)\n");
    printf("3. Calculate Resistance (R)\n");
    printf("Select: ");
    scanf("%d", &choice);

    if(choice == 1) {
        printf("Enter current I (A): "); 
        scanf("%lf", &I);
        printf("Enter resistance R (Ω): "); 
        scanf("%lf", &R);
        printf("Voltage V = %.3f V\n", I * R);
    } else if(choice == 2) {
        printf("Enter voltage V (V): "); 
        scanf("%lf", &V);
        printf("Enter resistance R (Ω): "); 
        scanf("%lf", &R);
        printf("Current I = %.3f A\n", V / R);
    } else if(choice == 3) {
        printf("Enter voltage V (V): "); 
        scanf("%lf", &V);
        printf("Enter current I (A): "); 
        scanf("%lf", &I);
        printf("Resistance R = %.3f Ω\n", V / I);
    }
}
void series_R_calculator(){
    int n;
    printf("\nNumber of resistors: ");
    scanf("%d", &n);

    double sum = 0;
    double r;
    for(int i = 1; i < n+1; i++) {
        printf("R%d = ", i);
        scanf("%lf", &r);
        sum += r;
    }
    printf("Total Series Resistance = %.3f Ω\n", sum);
}
void parallel_R_calculator(){
    int n;
    printf("\nNumber of resistors: ");
    scanf("%d", &n);

    double oversum = 0;
    double r;
    for(int i = 1; i < n+1; i++) {
        printf("R%d = ", i);
        scanf("%lf", &r);
        oversum += 1.0 / r;
    }
    printf("Total Parallel Resistance = %.3f Ω\n", 1.0 / oversum);
}
void rc_calculator(){
    double R, C;
    printf("\nEnter R (Ω): "); 
    scanf("%lf", &R);
    printf("Enter C (F): "); 
    scanf("%lf", &C);
    printf("Time Constant τ = RC = %.6f s\n", R * C);
}
void rl_calculator(){
    double R, L;
    printf("\nEnter L (H): "); 
    scanf("%lf", &L);
    printf("Enter R (Ω): "); 
    scanf("%lf", &R);
    printf("Time Constant τ = L/R = %.6f s\n", L / R);
}
void power_calculator(){
    double V, I;
    printf("\nEnter Voltage V (V): "); 
    scanf("%lf", &V);
    printf("Enter Current I (A): "); 
    scanf("%lf", &I);
    printf("Power P = VI = %.3f W\n", V * I);
}
void menu_item_1(void) {
    printf("\n>> Menu 1\n");
    printf("\nBasic circuit analyser\n");
    int choice = 0;

    do {
        printf("\n--- Basic Circuit Analysis ---\n");
        printf("1. Ohm's Law Calculator\n");
        printf("2. Series Resistors\n");
        printf("3. Parallel Resistors\n");
        printf("4. RC Time Constant\n");
        printf("5. RL Time Constant\n");
        printf("6. Power Calculator\n");
        printf("7. Exit\n");
        printf("Select: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: ohmsLaw_calculator(); 
                break;
            case 2: series_R_calculator(); 
                break;
            case 3: parallel_R_calculator(); 
                break;
            case 4: rc_calculator(); 
                break;
            case 5: rl_calculator(); 
                break;
            case 6: power_calculator(); 
                break;
            default:
                printf("Invalid choice.\n");
        }
    }while(choice != 7);
}





typedef enum {WAVE_SINE=1, WAVE_SQUARE=2, WAVE_TRIANGLE=3, WAVE_SAW=4} WaveType;
double sine_wave(double t, double freq, double amp, double dc) {
    return dc + amp * sin(2.0 * 3.14 * freq * t);
}
double square_wave(double t, double freq, double amp, double dc) {
    double v = sin(2.0 * 3.14 * freq * t);

    double result;

    if (v >= 0.0) 
        result = dc + amp * 1.0;
    else
        result = dc + amp * -1.0;

    return result;
}
double sawtooth_wave(double t, double freq, double amp, double dc) {
    double period = 1.0 / freq;
    double x = t - floor(t / period) * period;
    double val = 2.0 * (x / period) - 1.0;
    return dc + amp * val;
}
double triangle_wave(double t, double freq, double amp, double dc) {
    double s = sawtooth_wave(t, freq, 1.0, 0.0);
    double tri = 2.0 * fabs(s) - 1.0;
    return dc + amp * (-tri);
}
void ascii_plot(double *samples, int n, int height, int width) {
    if (n <= 0) 
        return;

    int i;
    int r;
    double min = samples[0];
    double max = samples[0];
    for (i = 1; i < n; i++) {
        if (samples[i] < min) 
            min = samples[i];
        if (samples[i] > max) 
            max = samples[i];
    }
    double range = max - min;
    if (range == 0) 
        range = 1.0;

    char *canvas = (char *)malloc(height * width);
    if (canvas==NULL) 
        return;

    for (i = 0; i < height * width; i++)
        canvas[i] = ' ';

    int step = n / width;
    if (step < 1) 
        step = 1;

    for (i = 0; i < width; i++) {
        int idx = i * step;
        if (idx >= n) idx = n - 1;

        double v = samples[idx];
        int row = (int)((v - min) / range * (height - 1));  
        int rrow = (height - 1) - row;
        canvas[rrow * width + i] = '*';
    }

    for (r = 0; r < height; r++) {
        printf("|");
        for (i = 0; i < width; i++)
            putchar(canvas[r * width + i]);
        printf("|\n");
    }

    printf("min=%.4g  max=%.4g\n", min, max);

    free(canvas);
}
int save_csv(const char *filename, double *samples, int n, double fs) {
    FILE *fp = fopen(filename, "w");
    if (fp==NULL) 
        return 0;

    fprintf(fp, "time_sec,value\n");

    for (int i = 0; i < n; i++) {
        double t = (double)i / fs;
        fprintf(fp, "%.9f,%.9f\n", t, samples[i]);
    }

    fclose(fp);
    return 0;
}
void menu_item_2(void) {
    printf("\n>> Menu 2\n");
    printf("\nSignal generator\n");
    printf("Supported waveforms: \n");
    printf("1. Sine\n");
    printf("2. Square\n");
    printf("3. Triangle\n");
    printf("4. Sawtooth\n");

    int choice;
    printf("Select waveform (1-4): ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid waveform.\n");
        return;
    }
    WaveType wf = (WaveType)choice;

    double freq, amp, dc, fs, duration;

    printf("Enter frequency (Hz): ");
    scanf("%lf", &freq);
    
    printf("Enter amplitude (peak): ");
    scanf("%lf", &amp);

    printf("Enter DC offset: ");
    scanf("%lf", &dc);

    printf("Enter sampling rate (Hz): ");
    scanf("%lf", &fs);

    if (fs < freq * 2) {
        printf("Warning: Sampling rate is too low\n");
    }

    printf("Enter duration (seconds): ");
    scanf("%lf", &duration);

    int n = (int)(fs * duration);
    if (n < 1) 
        n = 1;
    if (n > 10000000) {
        printf("Sample count too large, limiting to 10,000,000\n");
        n = 10000000;
    }

    double *samples = (double *)malloc(sizeof(double) * n);
    if (samples==NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        double t = (double)i / fs;
        switch (wf) {
            case WAVE_SINE:
                samples[i] = sine_wave(t, freq, amp, dc);
                break;
            case WAVE_SQUARE:
                samples[i] = square_wave(t, freq, amp, dc);
                break;
            case WAVE_TRIANGLE:
                samples[i] = triangle_wave(t, freq, amp, dc);
                break;
            case WAVE_SAW:
                samples[i] = sawtooth_wave(t, freq, amp, dc);
                break;
            default:
                samples[i] = 0.0;
        }
    }

    printf("\n--- First 20 samples ---\n");
    for (int i = 0; i < 20 && i < n; i++)
        printf("%.6f, %.6f\n", (double)i / fs, samples[i]);

    printf("\n--- ASCII Waveform ---\n");
    ascii_plot(samples, n, 20, 80);

    printf("\nSave data to CSV file? (y/n): ");
    char yn;
    while ((yn = getchar()) != EOF) {
        if (yn == '\n') continue;
        break;
    }

    if (yn == 'y' || yn == 'Y') {
        char name[256];
        printf("Enter filename: ");
        if (scanf("%255s", name) == 1) {
            if (save_csv(name, samples, n, fs))
                printf("Saved to %s\n", name);
            else
                printf("Failed to save file\n");
        }
    } else {
        printf("Skipping save\n");
    }

    free(samples);
}





double* read_csv(char *filename, int *n_out, double *fs_out)
{
    FILE *fp = fopen(filename, "r");
    if (fp==NULL) {
        printf("Cannot open file.\n");
        return NULL;
    }

    int m =1000;
    double *t = malloc(sizeof(double) * m);
    double *x = malloc(sizeof(double) * m);
    if (t==NULL || x==NULL) 
        return NULL;

    char line[256];
    int n = 0;
    while (fgets(line, sizeof(line), fp)) {
        double tt, vv;
        if (sscanf(line, "%lf,%lf", &tt, &vv) != 2) 
            continue;

        if (n >= m) {
            m *= 2;
            t = realloc(t, sizeof(double) * m);
            x = realloc(x, sizeof(double) * m);
        }
        
        t[n] = tt;
        x[n] = vv;
        n++;
    }
    fclose(fp);

    double dt = (t[n-1] - t[0]) / (n - 1);
    *fs_out = 1.0 / dt;
    *n_out = n;

    return x;
}
void compute_stats(double *a, int n, double *mean, double *rms, double *minv, double *maxv)
{
    double s1 = 0, s2 = 0;
    double mn = a[0], mx = a[0];

    for (int i = 0; i < n; i++) {
        s1 += a[i];
        s2 += a[i] * a[i];
        if (a[i] < mn) 
            mn = a[i];
        if (a[i] > mx) 
            mx = a[i];
    }

    *mean = s1 / n;
    *rms = sqrt(s2 / n);
    *minv = mn;
    *maxv = mx;
}
double zero_freq(double *a, int n, double fs)
{
    int count = 0;
    double last = -1, all_p = 0;

    for (int i = 1; i < n; i++) {
        if ((a[i-1] <= 0 && a[i] > 0) || (a[i-1] >= 0 && a[i] < 0)) {

            double t0 = (i-1) / fs;
            double t1 = i / fs;
            double p = fabs(a[i-1]) / (fabs(a[i-1]) + fabs(a[i]));
            double tc = t0 + (t1 - t0) * p;

            if (last >= 0) {
                all_p += (tc - last);
                count++;
            }
            last = tc;
        }
    }

    if (count == 0) 
        return 0;

    return 1.0 / (all_p / count);
}
int main_freq(double *a, int n, double fs)
{
    int kmax = n / 2;
    int best_k = 0;
    double best_v = 0;

    for (int k = 0; k <= kmax; k++) {
        double re = 0, im = 0;

        for (int i = 0; i < n; i++) {
            double ang = 2 * 3.14 * k * i / n;
            re += a[i] * cos(ang);
            im -= a[i] * sin(ang);
        }

        double mag = sqrt(re*re + im*im);
        if (mag > best_v) {
            best_v = mag;
            best_k = k;
        }
    }
    return best_k;
}
void menu_item_3(void){
    printf("\n>> Menu 3\n");
    printf("\nSignal fequency analyser\n");
    printf(" 1. Read CSV\n ");
    printf("2. Synthetic\n");
    printf(" Select:");
    
    int choice;
    scanf("%d", &choice);

    double *x;
    int n;
    double fs;

    if (choice == 1) {
        char name[200];
        printf("Enter file: ");
        scanf("%s", name);
        x = read_csv(name, &n, &fs);
    } else {
        fs = 2000;
        n = 200;
        x = malloc(sizeof(double) * n);
        for (int i = 0; i < n; i++) {
            double t = i / fs;
            x[i] = sin(2*3.14*50*t);
        }
    }

    if (x==NULL) {
        printf("Load failed.\n");
        return;
    }
    
    double mean, rms, mn, mx;
    compute_stats(x, n, &mean, &rms, &mn, &mx);
    printf("Mean=%.3f  RMS=%.3f  Min=%.3f  Max=%.3f\n", mean, rms, mn, mx);

    double fz = zero_freq(x, n, fs);
    printf("Zero-cross freq = %.2f Hz\n", fz);

    int k = main_freq(x, n, fs);
    printf("DFT main freq = %.2f Hz\n", k * (fs / n));
}





void current_converter(){
    double A;
    printf("\nEnter current (A): ");
    scanf("%lf", &A);

    printf("mA = %.6f mA\n", A * 1000);
}
void voltage_converter() {
    double V;
    printf("\nEnter voltage (V): ");
    scanf("%lf", &V);

    printf("mV = %.6f mV\n", V * 1000);
    printf("kV = %.6f kV\n", V / 1000);
}
void resistance_converter() {
    double R;
    printf("\nEnter resistance (Ω): ");
    scanf("%lf", &R);

    printf("kΩ = %.6f kΩ\n", R / 1000);
    printf("MΩ = %.6f MΩ\n", R / 1e6);
}
void power_converter() {
    double W;
    printf("\nEnter power (W): ");
    scanf("%lf", &W);

    printf("mW = %.6f mW\n", W * 1000);

    double dBm = 10 * log10(W * 1000);
    printf("dBm = %.6f dBm\n", dBm);
}
void frequency_converter() {
    double Hz;
    printf("\nEnter frequency (Hz): ");
    scanf("%lf", &Hz);

    printf("kHz = %.6f kHz\n", Hz / 1000);
    printf("MHz = %.6f MHz\n", Hz / 1e6);
    printf("GHz = %.6f GHz\n", Hz / 1e9);

    printf("ω (rad/s) = %.6f\n", 2 * 3.14 * Hz);
}
void capacitance_converter() {
    double F;
    printf("\nEnter capacitance (F): ");
    scanf("%lf", &F);

    printf("mF = %.6f mF\n", F * 1000);
    printf("µF = %.6f µF\n", F * 1e6);
    printf("nF = %.6f nF\n", F * 1e9);
    printf("pF = %.6f pF\n", F * 1e12);
}
void inductance_converter() {
    double H;
    printf("\nEnter inductance (H): ");
    scanf("%lf", &H);

    printf("mH = %.6f mH\n", H * 1000);
    printf("µH = %.6f µH\n", H * 1e6);
}
void menu_item_4(void) {
    printf("\n>> Menu 4\n");
    printf("\nUnit converter\n");
    int choice = 0;

    while (choice != 8) {
        printf("\n--- Engineering Unit Converter ---\n");
        printf("1. Voltage Converter (V, mV, kV)\n");
        printf("2. Current Converter (A, mA)\n");
        printf("3. Resistance Converter (Ω, kΩ, MΩ)\n");
        printf("4. Power Converter (W, mW, dBm)\n");
        printf("5. Frequency Converter (Hz → kHz → MHz → rad/s)\n");
        printf("6. Capacitance Converter (F, mF, µF, nF, pF)\n");
        printf("7. Inductance Converter (H, mH, µH)\n");
        printf("8. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: voltage_converter(); 
                break;
            case 2: current_converter(); 
                break;
            case 3: resistance_converter(); 
                break;
            case 4: power_converter(); 
                break;
            case 5: frequency_converter(); 
                break;
            case 6: capacitance_converter(); 
                break;
            case 7: inductance_converter(); 
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
}

