# Process injection techniques
## Shellcode injection
Victim process source code:

![pic0](./pics/Screenshot_0.png)

It shows messagebox:

![pic5](./pics/Screenshot_5.png)

VA of caption and text:

![pic1](./pics/Screenshot_1.png)

As you can see, caption and text are in .rdata section. BaseImage and .rdata section VA:

![pic2](./pics/Screenshot_2.png)

So, RVA of .rdata is 0x2000, RVA of caption and text is 0x2100 and 0x20F8. Read and rewrite them:

![pic3](./pics/Screenshot_3.png)

Than create simple shellcode shows the second messagebox with "Injected" text

![pic8](./pics/Screenshot_8.png)

Correct caption and text addresses in shellcode and add ascii string "Injected" to the end of shellcode

![pic4](./pics/Screenshot_4.png)

Run it

![pic6](./pics/Screenshot_6.png)

Result:

![pic7](./pics/Screenshot_7.png)

## PE injection
bla bla
## DLL injection
bla bla 
