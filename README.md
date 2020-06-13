# Construction of length and rate adaptive MET QC-LDPC Codes
This project contain Matlab platform (toolchain)  to construction Length and Rate adaptive codes MET QC-LDPC Codes from article U. Vasiliy, E. Sergey and G. Svistunov, "Construction of Length and Rate Adaptive MET QC-LDPC Codes by Cyclic Group Decomposition," 2019 IEEE East-West Design & Test Symposium (EWDTS), Batumi, Georgia, 2019, pp. 1-5.


![alt text](https://github.com/Lcrypto/Length-und-Rate-adaptive-code/blob/master/MET_LDPC_2013.jpg)

It allow to make several step sieving by lifting underdefined constrains from protograph based on: 
![alt text](https://www.google.com/search?q=Construction+of+Length+and+Rate+Adaptive+MET+QC-LDPC+Codes+by+Cyclic+Group+Decomposition&sxsrf=ALeKk03bd-uv9YX-saMfe1RdQnUUh-oggQ:1592058986590&source=lnms&tbm=isch&sa=X&ved=2ahUKEwiLp-3ygf_pAhWxxIsKHYKUDpUQ_AUoAXoECAsQAw&biw=1920&bih=947#imgrc=jm69lizAxsLY-M)

graph properties(girth,EMD);

code properties;

perfomance under simulation; 

recoverability of VNs and etc.


It support multi-treads, float and fix-point simulation. We suggest instead of simulation use Importance Sampling (https://github.com/Lcrypto/trapping-sets-enumeration) for low level of Bit error Rate(Block error rate). Length adaptive lifting (cyclic group decomprosition, multi families floor lifting) approach could be changed by any another type as well (e. g. floor-scale modular lifting, https://github.com/Lcrypto/floor-scale-modular-lifting-of-MET-LDPC-Codes). Additional parameters for sieving: spectral based Tanner-Vontobel-Koetter lower bound on minimum Pseudo-Weight and code weight (https://github.com/Lcrypto/GPU_implemetation_of_Tanner_lower_bound), EMD Spectrum shape (https://github.com/Lcrypto/EMD-Spectrum-LDPC), erasure recovery capability(https://github.com/Lcrypto/puncturing-optimization) could be applied as another stage of codes sieving.
