const std = @import("std");

var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
const EnumMap = std.enums.EnumMap;

const allocator = arena.allocator();

pub fn Option(comptime T: type) type {
    return union(enum) {
        none: void,
        some: T,

        fn is_some(self: @This()) bool {
            return switch (self) {
                .none => false,
                .some => |_| true,
            };
        }
        fn is_none(self: @This()) bool {
            return is_some(self) == false;
        }
        fn unwrap(self: @This()) T {
            return switch (self) {
                .none => unreachable,
                .some => |x| x,
            };
        }
        fn unwrap_or(self: @This(), default: T) T {
            return switch (self) {
                .none => default,
                .some => |x| x,
            };
        }
    };
}

pub fn LinkedList(comptime Value: type) type {
    return struct {
        const This = @This();

        const Node = struct {
            value: Value,
            next: ?*Node,
        };

        head: ?*Node,
        tail: ?*Node,

        pub fn init() This {
            return LinkedList(Value){
                .head = null,
                .tail = null,
            };
        }

        pub fn add(this: *This, value: Value) !void {
            var new_node = try allocator.create(Node);
            new_node.* = .{ .value = value, .next = null };

            if (this.tail) |tail| {
                tail.next = new_node;
                this.tail = new_node;
            } else if (this.head) |head| {
                head.next = new_node;
                this.tail = new_node;
            } else {
                this.head = new_node;
            }
        }
    };
}
pub fn main() anyerror!void {
    var l1 = LinkedList(i32).init();

    try l1.add(1);
    try l1.add(2);
    try l1.add(4);
    try l1.add(3);

    var h = l1.head;

    while (h) |head| : (h = head.next) {
        std.log.info("> {}", .{head.value});
    }
}
