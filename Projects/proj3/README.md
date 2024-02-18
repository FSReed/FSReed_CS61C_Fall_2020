# CS61CPU

Look ma, I made a CPU! Here's what I did:

## ALU

## Register file

## Single addi

- When decoding the instruction `addi`, I use a `mux` with `funct3` being the selector to select the value of `ALUSel`. But `sra` and `srl` have the same `funct3` code, so I use the `30`th bit to identify the `ALUSel` code of these two operations.

![ALUSel](./Images/proj3_3.png)
