# mod_vhost_alias_hostname

An Apache module that stores the `Host` header of the HTTP request in the apache's scoreboard.
It's useful to display the `VHost` (that otherwise would be empty) in `mod_status` when you're using
`mod_vhost_alias` in order to creates dynamically configured virtual hosts.



## Requiriments

*  apache >= 2.4
*  mod_vhost_alias


## Getting Started


### Install as DSO


If you have got the apxs2 (APache eXtenSion tool) tool installed, write the
following commands to build module:

```
$ tar xzvf mod_vhost_alias_hostname.tar.gz
$ cd mod_vhost_alias_hostname
$ make
$ make install
```

Check that in the main config file of your web server there is the following command:

LoadModule vhost_alias_hostname_module /usr/lib/apache2/modules/mod_vhost_alias_hostname.so

(The path to mod_vhost_alias_hostname.so depends on your apache installation)
