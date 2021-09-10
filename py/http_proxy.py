import socketserver
import http.server
import urllib


class Proxy(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.copyfile(urllib.urlopen(self.path), self.wfile)


httpd = socketserver.ForkingTCPServer(('', 3128), Proxy)
httpd.serve_forever()
