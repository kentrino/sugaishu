require('prime')

def check(primes, n)
  d = []
  d[0] = primes
  d[1] = primes.map{ |i| i * n } 
  d[2] = primes.map{ |i| i * n ** 2 } 
  d[3] = primes.map{ |i| i * n ** 3 }

  all_non_zero = true

  (2..4).each do |digits|
    (0..3).to_a.permutation(digits).each do |c|
      number = c.map.with_index{ |i, j| d[j][i] }.inject(:+)
      non_zero = number % 7 != 0
      return false if !non_zero
      all_zero &= non_zero
    end
  end
  return all_non_zero
end

# (set 4) Sugaish-checkをpassし得る4つのF_(base)の元の集合
# mod (base)で調べて(set 4)の集合を返す
def generate_set(base)
  result = []
  # mod 7では7は全てOK
  a = (1..(base - 1)).to_a
  (1..(base - 1)).each do |n|
    ok_set = []
    (0..((base - 1) ** 4 - 1)).each do |i|
      primes = i.to_s(base - 1).rjust(4, "0").split('').map{ |c| c.to_i }.map{ |i| a[i] }
      if check(primes, n)
        ok_set.push(primes)
      end
    end
    result[n] = ok_set
  end
  result
end

# (set 3) Sugaish-checkをpassし得る3つのF_(base)の元の集合
# (set 4)を(set 3)に変換
def squash_set(set_4)
  set_3 = []

  return if set_4 == nil 

  set_4.each do |a|
    (0..3).each do |filtered_index|
      set_3.push(a.select.with_index { |_, i| i != filtered_index }.sort)
    end
  end

  set_3.uniq!

  set_3.sort! do |a, b|
    a.inject(:+) <=> b.inject(:+)
  end

  set_3
end

set_3s = generate_set(7).map do |set_4|
  squash_set(set_4)
end.to_a

def set_3_to_string(set_3)
  return "  {}" if set_3 == nil || set_3.size == 0
  str = "  {\n    "
  str += set_3.map { |a| '{' + a.join(', ') + "}" }.join(",\n    ") + "\n  }"
  str
end

print set_3s.map { |set_3| set_3_to_string(set_3) }.join(",\n")
