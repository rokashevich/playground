import argparse
import asyncio
from dataclasses import dataclass
import os
import shlex
import sys
import psycopg2
from psycopg2 import sql
import time


host = "HHH"
database = "monitordb"
user = "YYY"
password = "XXX"
schema = "monitor"
def perform_database_operations():
    try:
        # Connect to the PostgreSQL database
        conn = psycopg2.connect(
            host=host,
            database=database,
            user=user,
            password=password
        )
        cur = conn.cursor()

        # 1. Check if the table "monitor" exists and create it if not
        create_table_query = sql.SQL("""
        CREATE TABLE IF NOT EXISTS {schema}.{table} (
            string TEXT,
            time TIMESTAMP,
            int INTEGER,
            bool BOOLEAN
        )
        """).format(schema=sql.Identifier(schema), table=sql.Identifier("monitor"))

        cur.execute(create_table_query)
        conn.commit()

        # 2. Check if a row with the specified string value exists
        string_value = "name n"
        check_query = sql.SQL("""
        SELECT EXISTS (
            SELECT 1 FROM {schema}.{table} WHERE string = %s
        )
        """).format(schema=sql.Identifier(schema), table=sql.Identifier("monitor"))

        cur.execute(check_query, (string_value,))
        exists = cur.fetchone()[0]

        if not exists:
            # 3. Insert the initial row if it does not exist
            insert_query = sql.SQL("""
            INSERT INTO {schema}.{table} (string, time, int, bool)
            VALUES (%s, %s, %s, %s)
            """).format(schema=sql.Identifier(schema), table=sql.Identifier("monitor"))

            # Example values for the initial insert
            initial_time = '2024-07-29 12:00:00'  # Replace with the actual initial time if needed
            initial_int = 0
            initial_bool = False

            cur.execute(insert_query, (string_value, initial_time, initial_int, initial_bool))
            conn.commit()
        else:
            # 2. Update the table where string == 'name n'
            update_query = sql.SQL("""
            UPDATE {schema}.{table}
            SET time = CURRENT_TIMESTAMP, int = %s, bool = %s
            WHERE string = %s
            """).format(schema=sql.Identifier(schema), table=sql.Identifier("monitor"))

            # Example values for int and bool
            int_value = 42
            bool_value = True
            string_value = "name n"

            cur.execute(update_query, (int_value, bool_value, string_value))
            conn.commit()

        # 3. Retrieve all rows from the table
        select_query = sql.SQL("""
        SELECT * FROM {schema}.{table}
        """).format(schema=sql.Identifier(schema), table=sql.Identifier("monitor"))

        cur.execute(select_query)
        rows = cur.fetchall()

        # Print the rows or process them as needed
        for row in rows:
            print(row)

    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        # Ensure the cursor and connection are closed
        if cur:
            cur.close()
        if conn:
            conn.close()




queue = asyncio.Queue()


async def printer():
    print(queue)
    while True:
        message = await queue.get()
        if message is None:  # Exit condition
            break
        print("!!!!!!!"+message)
        queue.task_done()

from http.server import BaseHTTPRequestHandler, HTTPServer
from socketserver import ThreadingMixIn
import json
class RequestHandler(BaseHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        self.loop = kwargs.pop('loop')
        super().__init__(*args, **kwargs)
    def do_GET(self):
        if self.path == "/metrics":
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()

            # Retrieve shared data
            self.wfile.write(json.dumps({"a":1}).encode())
    def log_message(self, format, *args):
        # Customize log message format here
        print("log_message")
        message = f">>>>>>{self.client_address[0]} - - [{self.log_date_time_string()}] {format % args}"
        asyncio.run_coroutine_threadsafe(queue.put(message), self.loop)
        print(queue)

    # def log(self, message):
    #     # Output the log message to a specific destination or format it differently
    #     print(f"Custom Log: {message}")

class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """Handle requests in a separate thread."""

@dataclass
class App:
    cmd: str
    name: str = ''
    args: tuple = ()
    killable: bool = False
    process: asyncio.subprocess.Process = None
    enabled: bool = True
    task: asyncio.Task = None
    stdout_task: asyncio.Task = None
    stderr_task: asyncio.Task = None
    restarts: int = 0
    fgcolor: str = ''
    def __post_init__(self):
        shlexed = shlex.split(self.cmd)
        self.name = shlexed[0]
        self.args = shlexed[1:]
        fgcolors = {'red':31,'green':32,'yellow':33,'blue':34,'magenta':34,'cyan':36,'white':37}

async def run_app(app):
    while True:
        os.environ["PYTHONUNBUFFERED"] = "1"
        app.process = await asyncio.create_subprocess_exec(
            app.name,
            *app.args,
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE,
        )

        print(f"Started {app.name} with PID {app.process.pid}")

        async def read_stream(stream, callback):
            while True:
                line = await stream.readline()
                if not line:
                    break
                await callback(line.decode().strip())

        app.stdout_task = asyncio.create_task(read_stream(app.process.stdout, lambda line: queue.put(f"[{app.name} stdout] {line}")))
        app.stderr_task = asyncio.create_task(read_stream(app.process.stderr, lambda line: queue.put(f"[{app.name} stderr] {line}")))

        await asyncio.wait([app.stdout_task, app.stderr_task])
        await app.process.wait()


async def main(apps):
    loop = asyncio.get_event_loop()
    httpd = ThreadedHTTPServer(('', 8000), lambda *args, **kwargs: RequestHandler(*args, loop=loop, **kwargs))
    loop.run_in_executor(None, httpd.serve_forever)
    consumer_task = asyncio.create_task(printer())


    while True:
        await queue.put("xxx")



        perform_database_operations()

        for app in apps:
            if app.enabled and not app.process:
                app.task = asyncio.create_task(run_app(app))
        await asyncio.sleep(1)


# hash_value = hash(s)
# return (hash_value % N) + 1

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', action='append', type=str, help='command', default=[])
    parser.add_argument('-k', action='append', type=str, help='killable', default=[])
    args = parser.parse_args()

    apps = []
    for cmd in args.c:
        apps.append(App(cmd))
    for cmd in args.k:
        apps.append(App(cmd, killable=True))

    asyncio.run(main(apps))
