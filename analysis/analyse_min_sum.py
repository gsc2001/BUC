import sys
import pickle as pkl
import subprocess


def main():
    binary_file_path = sys.argv[1]
    data_path = sys.argv[2]

    run_times = []
    for min_sup in range(1,21):
        print(f'running .. {min_sup}')
        block_size_bytes = 512 * 1024
        output = subprocess.run(f"echo {data_path} {block_size_bytes} {min_sup} | {binary_file_path}", capture_output=True,
                                shell=True)
        run_time = int(output.stdout.decode('utf-8').strip('\n'))
        run_times.append(run_time)
        print(f'ran .. {min_sup}, time = {run_time}')

    with open('min_sup_analysis.pkl', 'wb') as f:
        pkl.dump(run_times,f)
    print(run_times)

if __name__ == '__main__':
    main()
