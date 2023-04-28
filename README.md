# Construction of length and rate adaptive MET QC-LDPC Codes
The GitHub repository contains a MATLAB platform for constructing Length and Rate adaptive codes MET QC-LDPC Codes based on the article "Construction of Length and Rate Adaptive MET QC-LDPC Codes by Cyclic Group Decomposition" by U. Vasiliy, E. Sergey, and G. Svistunov, published in the 2019 IEEE East-West Design & Test Symposium.

This toolchain includes various modules and functions required to implement the construction of length and rate adaptive MET QC-LDPC codes using cyclic group decomposition. The provided code supports several stages of sieving, from graph properties and code properties to performance under simulation and recoverability of variable nodes (VNs). Additionally, it allows for multi-threading and float or fix-point simulation. Parameters such as spectral-based Tanner-Vontobel-Koetter lower bound on minimum Pseudo-Weight and code weight, EMD Spectrum shape, and erasure recovery capability can be applied as another stage of codes sieving.

The MATLAB platform provides further flexibility in terms of length adaptive lifting approaches, allowing researchers and practitioners to choose between different types such as cyclic group decomposition or floor-scale modular lifting of MET LDPC Codes, among others.

Overall, this repository offers a comprehensive MATLAB platform for constructing Length and Rate adaptive codes MET QC-LDPC Codes. With its many stages of sieving and support for various approaches, researchers and practitioners will find the toolchain valuable for exploring various strategies for designing efficient error correction systems with high-performance rates.

![alt text](https://github.com/Lcrypto/Length-und-Rate-adaptive-code/blob/master/MET_LDPC_2013.jpg)

It allow to make several step sieving by lenght and rate adaptive lifting underdefined constrains from protograph based on: 




graph properties(girth,EMD);

code properties;

perfomance under simulation; 

![alt text](https://github.com/Lcrypto/Length-und-Rate-adaptive-code/blob/master/Rate1_5_ITW2019_BLER1e-5_short.png)

recoverability of VNs and etc.





It support multi-treads, float and fix-point simulation. We suggest instead of simulation use Importance Sampling (https://github.com/Lcrypto/trapping-sets-enumeration) for low level of Bit error Rate(Block error rate). 

Length adaptive lifting  (cyclic group decomprosition, multi families floor lifting) approach could be changed by any another type as well (e. g. floor-scale modular lifting, https://github.com/Lcrypto/floor-scale-modular-lifting-of-MET-LDPC-Codes).

![alt text](https://github.com/Lcrypto/Length-und-Rate-adaptive-code/blob/master/Cyclic.png)

 Additional parameters for sieving: spectral based Tanner-Vontobel-Koetter lower bound on minimum Pseudo-Weight and code weight (https://github.com/Lcrypto/GPU_implemetation_of_Tanner_lower_bound), EMD Spectrum shape (https://github.com/Lcrypto/EMD-Spectrum-LDPC), erasure recovery capability(https://github.com/Lcrypto/puncturing-optimization) could be applied as another stage of codes sieving.
