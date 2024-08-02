import asyncpg
import asyncio

async def manage_database(host, port, dbname, schemaname):
    # Establish a connection to the database
    conn = await asyncpg.connect(host=host, port=port, user='your_user', password='your_password', database=dbname)
    
    # Create schema if it doesn't exist
    await conn.execute(f"CREATE SCHEMA IF NOT EXISTS {schemaname}")

    # Check if the table exists
    table_check = await conn.fetchval(f"""
        SELECT to_regclass('{schemaname}.mytable')
    """)

    # Create table if it doesn't exist
    if table_check is None:
        await conn.execute(f"""
            CREATE TABLE {schemaname}.mytable (
                string_column TEXT,
                bool_column BOOLEAN,
                int_column INTEGER,
                timestamp_column TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        """)
    
    # Example update based on string
    string_value = 'example_string'
    bool_value = True
    int_value = 123
    await conn.execute(f"""
        INSERT INTO {schemaname}.mytable (string_column, bool_column, int_column)
        VALUES ($1, $2, $3)
        ON CONFLICT (string_column) DO UPDATE SET 
            bool_column = EXCLUDED.bool_column,
            int_column = EXCLUDED.int_column,
            timestamp_column = CURRENT_TIMESTAMP
    """, string_value, bool_value, int_value)

    # Get all rows into a Python array
    rows = await conn.fetch(f"SELECT * FROM {schemaname}.mytable")

    # Close the connection
    await conn.close()

    # Return the rows
    return [dict(row) for row in rows]

# Example usage
async def main():
    rows = await manage_database('localhost', 5432, 'your_dbname', 'your_schemaname')
    print(rows)

# Run the main function
asyncio.run(main())
