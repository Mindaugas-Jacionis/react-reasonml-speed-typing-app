let component = ReasonReact.statelessComponent("Score");

let make = (~value=0, _children) => {
  ...component,
  render: _self =>
    <div> {ReasonReact.string("Score: " ++ string_of_int(value))} </div>,
};