cmd_/root/Little_Penguin/Assignment_01/Module.symvers := sed 's/\.ko$$/\.o/' /root/Little_Penguin/Assignment_01/modules.order | scripts/mod/modpost    -o /root/Little_Penguin/Assignment_01/Module.symvers -e -i Module.symvers   -T -
