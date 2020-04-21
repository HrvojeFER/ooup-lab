from abc import ABC, abstractmethod
from datetime import datetime, timedelta
import time


class NumberSequence:
    def __init__(self, source, *actions):
        self.source = source
        self.actions = actions
        self.sequence = []

    # A mix of template method and strategy is the most adequate design pattern for this.
    # Template method because we have a template method for running the number sequence.
    # Strategy because we have different strategies of dealing with the number source and actions.
    def run(self):
        while True:
            time_pre_op = datetime.now()

            next_number = self.source.get_next()
            if next_number is None:
                return

            self.sequence.append(next_number)
            for action in self.actions:
                action.do(self.sequence)

            time_post_op = datetime.now()

            if time_post_op > time_pre_op + timedelta(seconds=1) or time_pre_op == time_post_op:
                time.sleep(1)
            else:
                time.sleep((time_pre_op + timedelta(seconds=1) - time_post_op).microseconds / 1000000)


class NumberSource(ABC):
    @abstractmethod
    def get_next(self):
        pass


class NumberSequenceAction(ABC):
    @abstractmethod
    def do(self, sequence):
        pass


class KeyboardNumberSource(NumberSource):
    def get_next(self):
        n = None
        while n is None:
            string_input = input()
            if string_input == 'stop':
                return None

            try:
                n = float(string_input)
            except ValueError:
                print('Give me a number please!')
        return n


class FileNumberSource(NumberSource):
    def __init__(self, file_name):
        self._numbers, self._index = [], 0
        with open(file_name) as file:
            for x in file.read().split():
                try:
                    self._numbers.append(int(x))
                except ValueError:
                    continue

    def get_next(self):
        if self._index >= len(self._numbers):
            return None

        result = self._numbers[self._index]
        self._index += 1
        return result


class DumpToFile(NumberSequenceAction):
    def __init__(self, file_name_prefix):
        self._file_name_prefix = file_name_prefix

    def do(self, sequence):
        file_name = self._file_name_prefix + '_dump.txt'
        with open(file_name, 'w') as file:
            file.write('Number sequence dump at: %s \n' % datetime.now())
            for number in sequence:
                file.write(str(number) + '\n')
            file.flush()

        print('dumped to file: %s' % file_name)


class PrintSum(NumberSequenceAction):
    def do(self, sequence):
        print('sum: %f' % sum(sequence))


class PrintAverage(NumberSequenceAction):
    def do(self, sequence):
        print('average: %f' % (sum(sequence) / len(sequence)))


class PrintMedian(NumberSequenceAction):
    def do(self, sequence):
        if len(sequence) <= 0:
            print('median: %f' % 0)
        elif len(sequence) == 1:
            print('median: %f' % sequence[0])

        else:
            s, n = sorted(sequence), len(sequence)
            if n % 2 == 0:
                print('median: %f' % ((s[int(n / 2)] + s[int(n / 2 - 1)]) / 2))
            else:
                print('median: %f' % s[int(n / 2)])


class PrintSequence(NumberSequenceAction):
    def do(self, sequence):
        print('sequence: %s' % ' '.join(str(x) for x in sequence))


def number_sequence_main():
    input_file_name = 'number_sequence_input.txt'
    dump_file_prefix = 'number_sequence'

    keyboard = KeyboardNumberSource()
    file = FileNumberSource(input_file_name)

    dump_to_file = DumpToFile(dump_file_prefix)
    print_sum = PrintSum()
    print_average = PrintAverage()
    print_median = PrintMedian()
    print_sequence = PrintSequence()

    keyboard_dump_to_file = NumberSequence(keyboard, dump_to_file)
    file_print = NumberSequence(file, print_sum, print_average, print_median, print_sequence)

    keyboard_dump_to_file.run()
    file_print.run()
