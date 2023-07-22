import socketserver
import http.server
import urllib.request


class Proxy(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        print(self.path)
        self.copyfile(urllib.request.urlopen(self.path), self.wfile)


httpd = socketserver.ForkingTCPServer(('', 3128), Proxy)
httpd.serve_forever()
