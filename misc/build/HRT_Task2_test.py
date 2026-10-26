"""Generate test cases for HRT_Task2"""


def get_test_cases():
    tc1 = "AB" * 110000
    tc1_sol = ""

    tc2 = "CDABDCBDBADB"
    tc2_sol = "BDDB"

    test_cases = [tc1, tc2]
    solution = [tc1_sol, tc2_sol]
    return test_cases, solution

def main():
    input_file_name = "HRT_Task2_In"
    output_file_name = "HRT_Task2_Out"
    test_cases, solutions = get_test_cases()
    file_in_obj = open(input_file_name, "w+")
    for tc in test_cases:
        file_in_obj.write(tc + "\n")
    file_in_obj.close()

    file_out_obj = open(output_file_name, "w+")
    for solution in solutions:
        file_out_obj.write(solution + "\n")
    file_out_obj.close()

main()

