
    }
    
    *max_error = 0.0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            double error = fabs(A[i][j] - result[i][j]);
            if (error > *max_error) {
                *max_error = error;