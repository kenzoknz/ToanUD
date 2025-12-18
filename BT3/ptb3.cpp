#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//Solving a cubic equation using the discriminant approach
int main() 
{
    double a, b, c, d;
    cout << "Please enter space-separated a, b, c, d coefficients:\n";
    cin >> a >> b >> c >> d;
    
    b /= a;
    c /= a;
    d /= a;
    
    double disc, q, r, dum1, s, t, term1, r13;
    q = (3.0*c - (b*b))/9.0;
    r = -(27.0*d) + b*(9.0*c - 2.0*(b*b));
    r /= 54.0;
    disc = q*q*q + r*r;
    term1 = (b/3.0);
    
    double x1_real, x2_real, x3_real;
    double x2_imag, x3_imag;
    string x2_imag_s, x3_imag_s;
    if (disc > 0)   // One root real, two are complex
    {
        s = r + sqrt(disc);
        s = s<0 ? -cbrt(-s) : cbrt(s);
        t = r - sqrt(disc);
        t = t<0 ? -cbrt(-t) : cbrt(t);
        x1_real = -term1 + s + t;
        term1 += (s + t)/2.0;
        x3_real = x2_real = -term1;
        term1 = sqrt(3.0)*(-t + s)/2;
        x2_imag = term1;
        x3_imag = -term1;
        x2_imag_s =  " + "+ to_string(x2_imag) + "i";
        x3_imag_s =  " - "+ to_string(x2_imag) + "i";
    } 
    // The remaining options are all real
    else if (disc == 0)  // All roots real, at least two are equal.
    { 
        x3_imag = x2_imag = 0;
        r13 = r<0 ? -cbrt(-r) : cbrt(r);
        x1_real = -term1 + 2.0*r13;
        x3_real = x2_real = -(r13 + term1);
    }
    // Only option left is that all roots are real and unequal (to get here, q < 0)
    else
    {
        x3_imag = x2_imag = 0;
        q = -q;
        dum1 = q*q*q;
        dum1 = acos(r/sqrt(dum1));
        r13 = 2.0*sqrt(q);
        x1_real = -term1 + r13*cos(dum1/3.0);
        x2_real = -term1 + r13*cos((dum1 + 2.0*M_PI)/3.0);
        x3_real = -term1 + r13*cos((dum1 + 4.0*M_PI)/3.0);
    }
    
    cout << "\nRoots:" << endl <<
            "  x = " << x1_real << endl <<
            "  x = " << x2_real << x2_imag_s << endl <<
            "  x = " << x3_real << x3_imag_s << endl;
    
    return 0; 
}