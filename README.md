# Construction of length and rate adaptive MET QC-LDPC Codes
This project contain Matlab platform (toolchain)  to construction Length and Rate adaptive codes MET QC-LDPC Codes.
![alt text](https://www.google.com/search?q=usatyuk+vasiliy+ldpc&sxsrf=ALeKk02kPikx8JI1GJJ-_f_0MHSWKOPNKw:1592058496205&source=lnms&tbm=isch&sa=X&ved=2ahUKEwi20oKJgP_pAhUNzqQKHckmDbMQ_AUoAXoECAsQAw&biw=1920&bih=947#imgrc=2srxLWXF5WeqRM)

It allow to make several step sieving by lifting underdefined constrains from protograph based on: 


graph properties(girth,EMD);

code properties;

perfomance under simulation; 

recoverability of VNs and etc.


It support multi-treads, float and fix-point simulation. We suggest instead of simulation use Importance Sampling (https://github.com/Lcrypto/trapping-sets-enumeration) for low level of Bit error Rate(Block error rate). Length adaptive lifting (cyclic group decomprosition, multi families floor lifting) approach could be changed by any another type as well (e. g. floor-scale modular lifting, https://github.com/Lcrypto/floor-scale-modular-lifting-of-MET-LDPC-Codes). Additional parameters for sieving: spectral based Tanner-Vontobel-Koetter lower bound on minimum Pseudo-Weight and code weight (https://github.com/Lcrypto/GPU_implemetation_of_Tanner_lower_bound), EMD Spectrum shape (https://github.com/Lcrypto/EMD-Spectrum-LDPC), erasure recovery capability(https://github.com/Lcrypto/puncturing-optimization) could be applied as another stage of codes sieving.
