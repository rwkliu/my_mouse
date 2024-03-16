# frozen_string_literal: true

class MouseResolver
  attr_accessor :data, :header_line, :last_line, :map_height, :map_width, :chars

  def initialize
    self.data = []
    self.chars = ''
    self.map_height = 0
    self.map_width = 0
  end

  def load(data)
    index = 0

    data.each do |line|
      if index.zero?
        setHeaderLine(line)
      elsif index <= map_height
        self.data << line
      else
        setLastLine(line)
      end
      index += 1
    end
  end

  def setHeaderLine(header_line)
    @header_line = header_line
    self.map_height = header_line.to_i
    x_pos = header_line.index('x')
    raise "Invalid header, expected HEIGHTxWIDTH* o12 got #{header_line}" if x_pos.nil?

    self.map_width = header_line[x_pos + 1..].to_i
    self.chars = header_line[(map_height.to_s.size + map_width.to_s.size) + 1..].strip
  end

  def setLastLine(last_line)
    @last_line = last_line
  end

  def print
    p map_height
    p map_width
    p data
    p chars
  end

  def print_map
    data.each do |line|
      puts line
    end
  end

  def _find_entrance
    y = 0
    x = 0
    while y < data.size
      while x < data[y].size
        return [y, x] if data[y][x] == '1'

        x += 1
      end
      y += 1
    end
    [-1, -1]
  end

  def _where_to(y, x)
    [[y - 1, x], [y, x - 1], [y, x + 1], [y + 1, x]].each do |future_y, future_x|
      next if future_y.negative? || future_x.negative?
      next if future_y > map_height
      next if future_x > map_width

      return [future_y, future_x] if [chars[2], chars[4]].include?(data[future_y][future_x])
    end
    [-1, -1]
  end

  def resolve
    y, x = _find_entrance
    step = 0

    loop do
      print_map
      return step if data[y][x] == chars[4]
      break if (y == -1) || (x == -1)

      data[y][x] = '+'
      y, x = _where_to(y, x)
      step += 1
    end
    -1
  end

  def self.resolve(str_map)
    mr = MouseResolver.new
    mr.load(str_map.split("\n"))
    nbr_step = mr.resolve
    raise 'Exit not reached, invalid solution' if nbr_step == -1

    nbr_step
  end
end

def get_argf
  data = []
  ARGF.each do |line|
    data << line.strip
  end
  data
end

data = get_argf

p MouseResolver.resolve(data.join("\n"))
