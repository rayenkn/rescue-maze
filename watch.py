import subprocess, time

REPO = r"C:\Users\rayen\OneDrive\Documents\PlatformIO\Projects"

def has_changes():
    result = subprocess.run(
        ["git", "status", "--porcelain"],
        capture_output=True,
        cwd=REPO
    )
    return bool(result.stdout.strip())

def push():
    subprocess.run(["git", "add", "."], cwd=REPO)
    subprocess.run(["git", "commit", "-m", 
                   f"auto update {time.ctime()}"], cwd=REPO)
    subprocess.run(["git", "push", "origin", "main"], cwd=REPO)
    print(f"pushed at {time.ctime()}")

print("watching for changes...")
while True:
    if has_changes():
        push()
    time.sleep(5)