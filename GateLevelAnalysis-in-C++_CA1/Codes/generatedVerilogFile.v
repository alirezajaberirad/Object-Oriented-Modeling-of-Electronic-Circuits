module generatedModule(N1, N2, N3, N6, N7, N22, N23);

input N1, N2, N3, N6, N7;

output N22, N23;

wire N10, N11, N16, N19;

nand NAND2_2(N10, N1, N3); //its controllability is: 0.75
nand NAND2_6(N11, N3, N6); //its controllability is: 0.75
nand NAND2_1(N16, N2, N11); //its controllability is: 0.625
nand NAND2_3(N19, N11, N7); //its controllability is: 0.625
nand NAND2_4(N23, N16, N19); //its controllability is: 0.609375
nand NAND2_5(N22, N10, N16); //its controllability is: 0.53125

endmodule