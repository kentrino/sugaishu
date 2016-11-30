def mod_check(primes, n)
  d = []
  d[0] = primes
  d[1] = primes.map{ |i| i * n } 
  d[2] = primes.map{ |i| i * n ** 2 } 
  d[3] = primes.map{ |i| i * n ** 3 }

  (2..4).each { |digits|
    (0..3).to_a.permutation(digits).each { |c|
      number = c.map.with_index{ |i, j| d[j][i] }.inject(:+)
      return false if number % 7 == 0
    }
  }
  return true
end

(1..6).each do |n|
  (0..(6 ** 4 - 1)).each do |i|
    a = [1, 2, 3, 4, 5, 6]
    ps = i.to_s(6).rjust(4, "0").split('').map{ |c| c.to_i }.map{ |i| a[i] }
    print("#{n}: #{ps}\n") if mod_check(ps, n)
  end
end
