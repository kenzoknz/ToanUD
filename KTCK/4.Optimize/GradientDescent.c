#include <stdio.h>
#include <math.h>
//f(x) = (e^(3x) + 12x^2 + 5x)/(12 - 2x) - 25x
float function1(float x) {
    return (expf(3.0f * x) + 12.0f * x * x + 5.0f * x) / (12.0f - 2.0f * x) - 25.0f * x;
}

float derivativeFunction1(float x) {
    return ((3.0f * expf(3.0f * x) + 24.0f * x + 5.0f) * (12.0f - 2.0f * x) + 2.0f * (expf(3.0f * x) + 12.0f * x * x + 5.0f * x)) / ((12.0f - 2.0f * x) * (12.0f - 2.0f * x)) - 25.0f;
}

// gradient descent (no momentum)
float GradientDescent(float x_init, float learning_rate, int epochs, float (*gradFunc)(float), float (*objFunc)(float)) {
    float x = x_init;

    for (int i = 1; i <= epochs; ++i) {
        float x_prev = x;
        x = x - learning_rate * gradFunc(x);
        printf("Iteration %d: x = %.6f, function value = %.6f\n", i, x, objFunc(x));

        if (fabsf(x - x_prev) < 1e-5f) {
            printf("Convergence reached after %d iterations.\n", i);
            printf("Minimum value: %.8f\n", objFunc(x));
            printf("At point: x = %.8f\n", x);
            break;
        }
    }

    return objFunc(x);
}

int main(void) {
    float x_initial = -1.0f;
    float learning_rate = 0.001f;
    int epochs = 1000;

    printf("Function: f(x) = (e^(3x) + 12x^2 + 5x)/(12 - 2x) - 25x\n");
    printf("Initial point: x = %.6f\n", x_initial);
    printf("Learning rate (gamma): %.6f\n", learning_rate);
    printf("Maximum epochs: %d\n\n", epochs);

    GradientDescent(x_initial, learning_rate, epochs, derivativeFunction1, function1);

    return 0;
}
