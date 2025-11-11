## Compile and run the cpp program to generate memory log, quit after like a minute
import time
import os
import subprocess
import pandas as pd
import matplotlib.pyplot as plt

if os.path.exists('memory_log.csv'):
    os.remove('memory_log.csv')

# Option A: use project Makefile (preferred if present)
os.system('cd Excecises/src && make')



# Start the program town_sim.exe (Windows) or ./town_sim (Linux/Mac) then wait a bit  
print("Successfully compiled .Starting town_sim...")
# check were in the right directory
os.system("dir")
os.chdir("Excecises/src")  # Change to the directory where the executable is located
proc = subprocess.Popen(['./town_sim.exe' if os.name == 'nt' else './town_sim'])
try:
    print("Running town_sim for 60 seconds to collect memory usage data...")
    time.sleep(60)

finally:
    print("Finished running town_sim.")
    proc.terminate()
    proc.wait(timeout=5)

# Only proceed if memory_log.csv exists
os.chdir("../../")  # Change back to original directory
if not os.path.exists('memory_log.csv'):
    raise FileNotFoundError('memory_log.csv not created — program failed or MemoryTracker not initialized')

df = pd.read_csv('memory_log.csv')

plt.plot(df['rotation'], df['outstanding_allocations'])
plt.xlabel('Rotation')
plt.ylabel('Outstanding Allocations (bytes)')
plt.title('Memory Usage Over Time')
plt.grid()
plt.savefig('memory_usage.png')
plt.show()