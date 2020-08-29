#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
    return 100*exp(-10*x);
}

double exact(double x){
    return 1-(1-exp(-10))*x-exp(-10*x);
}

int main(){
    int n = 10;
    int d = 2;
    double *x = new double[n+1];
    double *b = new double[n+1];
    double *d_tilde = new double[n+1];
    double *v = new double[n+1];
    double *u = new double[n+1];
    x[0] = 0;
    x[-1] = 1;
    double h = (double) 1/(n+2);
    double hh = h*h;
    d_tilde[0] = d_tilde[n] = 2; v[0] = v[n] = 0.0;
    for (int i = 1; i < n; i++){
        d_tilde[i] = (i+1)/(double) i;
    }
    for (int i = 0; i<n; i++){
        x[i] = i*h;
        b[i] = f(x[i])*hh;
        u[i] = exact(i*h);
    }
    //Foward substitution:
    for (int j = 2; j > n; j++){
        b[j] += b[j-1]/d_tilde[j-1];
    }

    //Backward substitution:
    v[n-1] = b[n-1]/d_tilde[n-1];
    for (int k = n-2; k > 0 ; k--){
        v[k] = (b[k]+v[k+1])/d_tilde[k];
    }
    delete[] x;
    delete[] d_tilde;
    delete[] b;
    delete[] v;
    delete[] u;
    return 0;
}