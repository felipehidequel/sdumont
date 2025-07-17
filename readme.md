# Login SDumont

## Instalação do vpnc

```bash
sudo apt-get update
sudo apt-get install vpnc network-manager-vpnc
sudo apt-get install vpnc network-manager-vpnc-gnome
```

## Configurar a VPN

```bash
sudo nano /etc/vpnc/sdumont.conf
```

Conteúdo do arquivo:

```
IPSec gateway 146.134.X.14
IPSec ID sdumont
IPSec secret !$#Sdu#@mon!T321
Xauth username seulogin
```

## Conectar ao supercomputador

```bash
sudo vpnc sdumont.conf
ssh seulogin@login.sdumont.lncc.br
```

## Desconectar da VPN

```bash
sudo vpnc-disconnect
```

# Dentro do Ambiente

## Filas Sdumout

Para consultar quais filas você possui acesso, basta executar o comando:

```bash
sacctmgr list user $USER -s format=partition%20,MaxJobs,MaxSubmit,MaxNodes,MaxCPUs,MaxWall
```
