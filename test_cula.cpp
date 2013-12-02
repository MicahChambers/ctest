#include <cstdio>

#include <cula.hpp>

int MeetsMinimumCulaRequirements()
{
    int cudaMinimumVersion = culaGetCudaMinimumVersion();
    int cudaRuntimeVersion = culaGetCudaRuntimeVersion();
    int cudaDriverVersion = culaGetCudaDriverVersion();
    int cublasMinimumVersion = culaGetCublasMinimumVersion();
    int cublasRuntimeVersion = culaGetCublasRuntimeVersion();

    if(cudaRuntimeVersion < cudaMinimumVersion)
    {
        printf("CUDA runtime version is insufficient; "
               "version %d or greater is required\n", cudaMinimumVersion);
        return 0;
    }

    if(cudaDriverVersion < cudaMinimumVersion)
    {
        printf("CUDA driver version is insufficient; "
               "version %d or greater is required\n", cudaMinimumVersion);
        return 0;
    }

    if(cublasRuntimeVersion < cublasMinimumVersion)
    {
        printf("CUBLAS runtime version is insufficient; "
               "version %d or greater is required\n", cublasMinimumVersion);
        return 0;
    }

    return 1;
}


double mat[13*13] = {
2.68038, 1.78877, 2.5662, 2.59688, 2.82329, 1.3951, 1.67045, 2.53646, 1.55555, 2.10794, 1.95479, 2.25774, 1.72957, 
2.0268, 2.90446, 2.83239, 2.27142, 2.43459, 1.28321, 2.21394, 1.0326, 1.48577, 1.27446, 2.60835, 1.31336, 1.80189, 
1.25958, 1.21762, 2.99785, 1.43651, 2.02586, 2.67822, 2.22528, 1.59206, 2.2751, 2.04857, 1.98717, 2.94555, 1.58503, 
2.54272, 2.05349, 2.53983, 1.80046, 2.78306, 1.56663, 1.70492, 2.61545, 2.83805, 1.13951, 2.89865, 2.05199, 1.17211, 
1.38443, 2.32645, 2.78047, 1.69779, 1.12834, 1.04005, 1.9154, 1.12619, 1.47656, 2.94127, 2.80442, 2.70184, 1.53333, 
2.07952, 1.75041, 2.5205, 2.02507, 2.33545, 2.06321, 1.07856, 1.87528, 2.86367, 2.86162, 2.4419, 1.56859, 2.47707, 
2.27996, 1.7081, 2.37572, 1.33195, 1.88021, 2.76015, 2.6584, 1.66067, 1.45794, 2.78674, 1.70072, 2.37334, 2.91294, 
2.17728, 2.31461, 2.71735, 1.87912, 2.84794, 1.79687, 2.62953, 2.36844, 2.82194, 1.96498, 1.43165, 2.9005, 2.84026, 
1.29532, 2.76212, 2.28216, 1.86391, 2.23919, 1.56212, 2.572, 1.61492, 1.89407, 1.45221, 1.37507, 1.55247, 2.11289, 
1.833, 1.33921, 2.81361, 1.20634, 1.25215, 1.99089, 2.52095, 2.9695, 2.87001, 2.36889, 1.76638, 2.49954, 1.73733, 
1.58832, 1.46452, 2.16898, 1.48883, 1.30478, 2.4643, 1.25095, 2.58694, 1.3282, 2.49014, 1.14906, 2.90021, 1.10506, 
2.04313, 1.35242, 1.48012, 2.5956, 2.46531, 2.31313, 2.93481, 2.27892, 2.51947, 1.18696, 1.2698, 2.04042, 1.15646, 
1.13981, 1.40931, 1.92284, 2.63935, 2.14664, 2.51116, 1.10388, 1.31561, 2.99999, 1.40866, 2.77991, 1.25094, 2.9956
};

int main() {

	culaStatus s;

	s = culaInitialize();
	if(s != culaNoError)
	{
		    printf("%s\n", culaGetStatusString(s));
			    /* ... Error Handling ... */
	}
	
	/* ... Your code ... */
	
	
	culaShutdown();

}
