# Process injection techniques
## Shellcode injection
Victim process source code:

![pic0](./pics/Screenshot_0.png)

It shows messagebox:

![pic5](./pics/Screenshot_5.png)

VA of caption and text:

![pic1](./pics/Screenshot_1.png)

BaseImage and .rdata section VA:

![pic2](./pics/Screenshot_2.png)

So, RVA of caption and text is 0x2100 and 0x20F8. Read and rewrite them:

![pic3](./pics/Screenshot_3.png)
![pic4](./pics/Screenshot_4.png)

## PE injection
bla bla
## DLL injection
bla bla 
