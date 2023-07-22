// http://atom.local/jenkins/scriptApproval/
method groovy.lang.GString getBytes java.lang.String
method java.io.OutputStream write byte[]
method java.net.HttpURLConnection getErrorStream
method java.net.HttpURLConnection getResponseCode
method java.net.HttpURLConnection setRequestMethod java.lang.String
method java.net.URL openConnection
method java.net.URLConnection getInputStream
method java.net.URLConnection getOutputStream
method java.net.URLConnection setDoOutput boolean
staticMethod org.codehaus.groovy.runtime.DefaultGroovyMethods getText java.io.InputStream

// get/post https://stackoverflow.com/questions/25692515/groovy-built-in-rest-http-client
import groovy.json.JsonSlurper

Map tasks = [failFast: false]

def github_repo_size(String repo) {
    println("Hello World!")
    def get = new URL("https://api.github.com/repos/$repo").openConnection();
    def getRC = get.getResponseCode();
    println(getRC);
    if (getRC.equals(200)) {
        def data = get.getInputStream().getText()
        def jsonSlurper = new JsonSlurper()
        def o = jsonSlurper.parseText(data)
        assert o instanceof Map
        return o.size // kb
    }
    return 0
}

def push_to_pushgateway(int size) {
    def post = new URL("http://pushgateway-svc.my-prometheus:9091/pushgateway/metrics/job/cp19").openConnection();
    def message = """# TYPE github_repo_size gauge
# HELP github_repo_size Repo size from github api in KB.
github_repo_size $size
"""
    post.setRequestMethod("POST")
    post.setDoOutput(true)
    post.getOutputStream().write(message.getBytes("UTF-8"));
    def postRC = post.getResponseCode();
    //println(postRC+">>>"+post.getErrorStream().text);
    if (postRC.equals(200)) {
        println(post.getInputStream().getText());
    }
}

tasks[] = { ->
  node {
    stage("Build") {
      push_to_pushgateway(
        github_repo_size('rokashevich/rokashevich.github.io')
      )
    }
  }
}
stage("Outer") {
    parallel(tasks)
}