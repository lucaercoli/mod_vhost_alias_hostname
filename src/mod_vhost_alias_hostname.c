/*
 *
 * Date:        2015/25/11
 * Info:        mod_vhost_alias_hostname Apache >= 2.4 module
 * Contact:     mailto: <luca.e [at] seeweb.it>
 * Version:     1.0
 * Author:      Luca Ercoli
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 */


#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_connection.h"
#include "mpm_common.h"
#include "ap_mpm.h"
#include "apr_strings.h"
#include "scoreboard.h"


module AP_MODULE_DECLARE_DATA vhost_alias_hostname_module;

char myVhost[32];


static int status_handler(request_rec *r)
{

    if ( apr_table_get(r->headers_in,"Host"))
    {

	memset(myVhost, '\0', sizeof(myVhost));

	apr_cpystrn(myVhost, apr_table_get(r->headers_in,"Host"), sizeof(myVhost));

	r->server->server_hostname = myVhost;

	(void)ap_update_child_status(r->connection->sbh, SERVER_BUSY_WRITE, r);
	
    }

    return DECLINED;
}



static void register_hooks(apr_pool_t *p)
{

    ap_hook_handler(status_handler, NULL, NULL, APR_HOOK_REALLY_FIRST);

}

AP_DECLARE_MODULE(vhost_alias_hostname) = {
    STANDARD20_MODULE_STUFF,
    NULL,                       /* create per-directory config structure */
    NULL,                       /* merge per-directory config structures */
    NULL,  /* create per-server config structure */
    NULL,                       /* merge per-server config structures */
    NULL,                  /* command apr_table_t */
    register_hooks              /* register hooks */
};
