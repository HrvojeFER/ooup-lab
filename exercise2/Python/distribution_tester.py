from abc import ABC, abstractmethod
import numpy as num


class DistributionTester:
    def __init__(self, num_gen, percent_test):
        self.num = num_gen
        self.percentile = percent_test

    def gen_nums(self):
        return list(self.num.gen())

    def get_percentile(self, nums, p):
        return self.percentile.get(nums, p)

    def get_average_percentile(self, p, n=10):
        return sum(self.get_percentile(self.gen_nums(), p) for _ in range(n)) / n


class NumberGeneratorStrategy(ABC):
    @abstractmethod
    def gen(self):
        pass


class GetPercentileStrategy(ABC):
    @abstractmethod
    def get(self, nums, p):
        pass


class SequentialNumberGenerator(NumberGeneratorStrategy):
    def __init__(self, start, end, step):
        self.start = start
        self.end = end
        self.step = step

    def gen(self):
        return range(self.start, self.end, self.step)


class NormalNumberGenerator(NumberGeneratorStrategy):
    def __init__(self, n, mean, dev):
        self.n = n
        self.mean = mean
        self.dev = dev

    def gen(self):
        return num.random.normal(size=self.n, loc=self.mean, scale=self.dev)


class ExponentialNumberGenerator(NumberGeneratorStrategy):
    def __init__(self, n, scale):
        self.n = n
        self.scale = scale

    def gen(self):
        return num.random.exponential(size=self.n, scale=self.scale)


class FibonacciNumberGenerator(NumberGeneratorStrategy):
    def __init__(self, n):
        self.n = n

    def gen(self):
        n0, n1 = 0, 1

        if self.n <= 0:
            return

        if self.n > 0:
            yield n0

            if self.n > 1:
                yield n1
                for _ in range(2, self.n):
                    n1 = n1 + n0
                    n0 = n1
                    yield n1


class ClosestPercentile(GetPercentileStrategy):
    @staticmethod
    def _get_closest(nums, p):
        return round(p * len(nums) / 100 - 0.5)

    def get(self, nums, p):
        nums = sorted(nums)
        if p <= 0:
            return nums[0]
        if p >= 100:
            return nums[len(nums) - 1]
        
        return nums[self._get_closest(nums, p)]


class InterpolatedPercentile(GetPercentileStrategy):
    @staticmethod
    def _get_percentile(n, i):
        return 100 * (i + 0.5) / n

    @classmethod
    def _get_interpolation(cls, nums, n, i, p):
        return nums[i] + n * (p - cls._get_percentile(n, i)) * (nums[i + 1] - nums[i]) / 100

    def get(self, nums, p):
        nums = sorted(nums)
        n = len(nums)
        if p >= self._get_percentile(n, n - 1):
            return nums[n - 1]
        if p <= self._get_percentile(n, 0):
            return nums[0]

        return self._get_interpolation(
            nums,
            n,
            next(i for i in range(n) if self._get_percentile(n, i) <= p < self._get_percentile(n, i + 1)),
            p)


def distribution_tester_main():
    one_to_ten = SequentialNumberGenerator(1, 11, 1)
    normal = NormalNumberGenerator(100, 1, 1)
    exponential = ExponentialNumberGenerator(100, 2)
    fibonacci = FibonacciNumberGenerator(10)

    closest = ClosestPercentile()
    interpolated = InterpolatedPercentile()

    one_to_ten_interpolated = DistributionTester(one_to_ten, interpolated)
    normal_closest = DistributionTester(normal, closest)
    exponential_closest = DistributionTester(exponential, closest)
    fibonacci_closest = DistributionTester(fibonacci, closest)

    for i in range(101):
        print('1...10 %dth percentile average interpolated: %f' %
              (i, one_to_ten_interpolated.get_average_percentile(i)))
        print('normal(mean = 1, dev = 1) %dth percentile closest average: %f' %
              (i, normal_closest.get_average_percentile(i)))
        print('exponential(scale = 2) %dth percentile closest average : %f' %
              (i, exponential_closest.get_average_percentile(i)))
        print('fibonacci(n = 10) %dth percentile closest: %f\n' %
              (i, fibonacci_closest.get_percentile(fibonacci_closest.gen_nums(), i)))
