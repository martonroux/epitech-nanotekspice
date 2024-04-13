def save_file(filename: str, data:str) -> None:
    with open(filename, "w") as f:
        f.write(data)
