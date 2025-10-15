import pandas as pg

# import mem csv 
df = pg.read_csv('memory_log.csv')

# plot the data
import matplotlib.pyplot as plt
plt.plot(df['rotation'], df['outstanding_allocations'])
# plt.plot(df2['rotation'], df2['outstanding_allocations'], label='Without memory leaks')
plt.xlabel('Rotation')
plt.ylabel('Outstanding Allocations (bytes)')
plt.title('Memory Usage Over Time')
plt.legend()
plt.grid()
plt.savefig('memory_usage.png')
plt.show()
plt.close()