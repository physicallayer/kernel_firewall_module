# kernel_firewall_module



## Collaborators

- [Sanghee Choi](https://github.com/pengin7384)
- [Hyeonhong Kim](https://github.com/khhis)
- [Dongwook Jeong](https://github.com/James-Jeong)
- [Jeonghyun Choi](...)
- [Janggun Lee](...)



## Compile

```
sudo apt-get install build-essential linux-headers-$(uname -r)
make
```



## Load

```
sudo insmod firewall.ko
```



## Remove

```
sudo rmmod firewall
```



## Test

```
dmesg -C
sudo insmod firewall.ko
...
sudo rmmod firewall
dmesg
```

