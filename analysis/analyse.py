import sys
import pickle as pkl
import subprocess


def main():
    binary_file_path = sys.argv[1]
    data_path = sys.argv[2]

    run_times = []
    for block_size in [8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]:
        print(f'running .. {block_size}')
        block_size_bytes = block_size * 1024
        output = subprocess.run(f"echo {data_path} {block_size_bytes} 10 | {binary_file_path}", capture_output=True,
                                shell=True)
        run_time = int(output.stdout.decode('utf-8').strip('\n'))
        run_times.append(run_time)
        print(f'ran .. {block_size}, time = {run_time}')

    with open('mem_analysis.pkl', 'wb') as f:
        pkl.dump(run_times,f)
    print(run_times)

if __name__ == '__main__':
    main()
