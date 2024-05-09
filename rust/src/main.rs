
pub fn add_checked(a: u128, b: u128) -> Option<u128> {
    let (c, overflow) = a.overflowing_add(b);
    if overflow {
        None
    } else {
        Some(c)
    }
}


fn main() {
    // get the input to the program
    let args: Vec<String> = std::env::args().collect();
    if args.len() == 2 {
        let x = args[1].parse::<u128>().unwrap();
        let y = args[2].parse::<u128>().unwrap();
        let z = add_checked(x, y);
        match z {
            Some(z) => println!("{} + {} = {}", x, y, z),
            None => println!("{} + 1 overflowed!", x),
        }
    } else {
        println!("Please provide one argument to this program");
    }
}