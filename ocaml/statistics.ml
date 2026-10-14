
let rec read_positive_count () =
  print_string "Enter the number of integers: ";
  flush stdout;

  try
    let count = int_of_string (read_line ()) in
    if count > 0 then count
    else (
      print_endline "Please enter a positive number.";
      read_positive_count ()
    )
  with
  | Failure _ ->
      print_endline "Invalid input. Please enter an integer.";
      read_positive_count ()

let rec read_numbers count index =
  if index > count then []
  else (
    Printf.printf "Enter integer %d: " index;
    flush stdout;

    try
      let number = int_of_string (read_line ()) in
      number :: read_numbers count (index + 1)
    with
    | Failure _ ->
        print_endline "Invalid input. Please enter an integer.";
        read_numbers count index
  )

let calculate_mean numbers =
  match numbers with
  | [] -> invalid_arg "Cannot calculate statistics for an empty list"
  | _ ->
      let total =
        List.fold_left
          (fun sum number -> sum +. float_of_int number)
          0.0 numbers
      in
      total /. float_of_int (List.length numbers)


let calculate_median numbers =
  match numbers with
  | [] -> invalid_arg "Cannot calculate statistics for an empty list"
  | _ ->
      let sorted = List.sort compare numbers in
      let size = List.length sorted in
      let middle = size / 2 in

      if size mod 2 = 1 then
        float_of_int (List.nth sorted middle)
      else
        let left = float_of_int (List.nth sorted (middle - 1)) in
        let right = float_of_int (List.nth sorted middle) in
        (left +. right) /. 2.0

let calculate_mode numbers =
  match numbers with
  | [] -> invalid_arg "Cannot calculate statistics for an empty list"
  | _ ->
      let frequencies =
        List.fold_left
          (fun counts number ->
            let previous =
              try List.assoc number counts
              with Not_found -> 0
            in
            (number, previous + 1) :: List.remove_assoc number counts)
          [] numbers
      in

      let highest_frequency =
        List.fold_left
          (fun highest (_, frequency) -> max highest frequency)
          0 frequencies
      in

      frequencies
      |> List.filter (fun (_, frequency) ->
           frequency = highest_frequency)
      |> List.map fst
      |> List.sort compare

let () =
  print_endline "OCaml - Functional Statistics Calculator";

  try
    let count = read_positive_count () in
    let numbers = read_numbers count 1 in

    Printf.printf "\nNumbers: %s\n"
      (numbers
       |> List.map string_of_int
       |> String.concat ", ");

    Printf.printf "Mean: %.2f\n" (calculate_mean numbers);
    Printf.printf "Median: %.2f\n" (calculate_median numbers);

    Printf.printf "Mode: %s\n"
      (calculate_mode numbers
       |> List.map string_of_int
       |> String.concat ", ")
  with
  | End_of_file ->
      prerr_endline "\nInput ended unexpectedly."

