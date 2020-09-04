#include <stdio.h>

#include <pci/pci.h>

int main()
{
  struct pci_access *pacc;
  struct pci_dev *dev;
  unsigned int c;
  char namebuf[1024], *name;

  pacc = pci_alloc();
  pci_init(pacc);
  pci_scan_bus(pacc);
  printf("vendoID -- deviceID -- class\n");
  for (dev=pacc->devices; dev; dev=dev->next)
    {
      printf("---------------------\n");
      pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
      c = pci_read_byte(dev, PCI_INTERRUPT_PIN);
      printf("0x%04x -- 0x%04x -- 0x%04x\n", dev->vendor_id, dev->device_id, dev->device_class);
      name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_VENDOR, dev->vendor_id, dev->device_id);
      printf("%s\n", name);
      name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
      printf("%s\n", name);
      printf("---------------------\n");
    }
  pci_cleanup(pacc);
  return 0;
}
